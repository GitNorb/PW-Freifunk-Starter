<?php
include_once('scripts/node_migration.php');

if($input->urlSegment2) throw new Wire404Exception();

if($input->urlSegment1){
  switch($input->urlSegment1){
    case 'list':
      $nodes = $pages->find('template=node, sort=-subtitle');
      $table = '';

      foreach($nodes as $node){

        $table .="<tr class='".($node->online == 1 ? "alert success" : "alert danger")."'>
                  <td>$node->subtitle</td>
                  <td>$node->title</td>
                  <td>$node->latitude</td>
                  <td>$node->longitude</td>
                  <td>".($node->online == 1 ? "online" : "offline")."</td>
                  <td><a href='{$pages->get('/profile/')->httpUrl}{$node->operator->name}'>{$node->operator->name}</a></td>
                </tr>";
      }

      $page->table = $table;
      $content = renderPage();
      break;
    case 'map':
      // Site settings
      $config->styles->add($config->urls->templates.'css/leaflet.css');
      $config->scripts->add($config->urls->templates.'js/leaflet-src.js');
      $fullwidth = true;

      $content= "<div id='map' style='width:100%' class='map'></div>";

      // Find all nodes with coordinate
      $nodes = $pages->find("template=node, latitude!=''");
      $marker = '';

      // create the node markers
      foreach($nodes as $node){
        $marker .= "L.circle([{$node->latitude}, {$node->longitude}], 10, {
                                  color:".($node->online == 1 ? "'blue'" : "'red'").",
                                  fillColor: ".($node->online == 1 ? "'blue'" : "'red'")."
                    }).addTo(map)
                      .bindPopup('{$node->subtitle}');";
      }

      // create the Map with Markers
      $script = "<script>
                var map = L.map('map').setView([50.3588, 7.48407], 10);
                var besuch = new Date().getHours();

                if (besuch < 22 || besuch > 6) {
                  // Tagesansicht
                  L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
                    maxZoom: 19,
                    attribution: '&copy; <a href=\"http://www.openstreetmap.org/copyright\">OpenStreetMap</a>'
                  }).addTo(map);
                } else {
                  // Nachtansicht
                  L.tileLayer('http://{s}.tiles.wmflabs.org/bw-mapnik/{z}/{x}/{y}.png', {
                    maxZoom: 19,
                    attribution: '&copy; <a href=\"http://www.openstreetmap.org/copyright\">OpenStreetMap</a>'
                  }).addTo(map);
                }

                // Geolokalisierung
                map.locate({setView: true, maxZoom: 16});

                // Zoom to current possition
                function onLocationFound(e) {
                  var radius = e.accuracy / 2;

                  L.circle(e.latlng, radius).addTo(map)
                      .bindPopup(\"You are within \" + radius + \" meters from this point\").openPopup();

                  L.circle(e.latlng, radius).addTo(map);
                }

                // sobald coordinaten gefunden wurden
                map.on('locationfound', onLocationFound);


                  $marker

                  map.on('click', function(e){
                    alert('Geoposition = ' + e.latlng);
                  })
                  $('#map').height($(window).height() - 205).width($(window).width());
                    map.invalidateSize();
                  </script>";

      break;
    case 'add':
      // Check if user is logged in and save the input->get in the session variable.
      if(!wire('user')->isLoggedin()){
        $content = "<article><h2>Gesicherte Seite</h2>Bitte Anmelden oder Registrieren.</article>";
        $session->redirectUrl = $page->path."add/";
        if(isset($input->get->mac)) $session->mac = $sanitizer->text($input->get->mac);
        if(isset($input->get->key)) $session->key = $sanitizer->text($input->get->key);
      } elseif(!$input->post->submit) {
        if(isset($input->get->mac)) $session->mac = $sanitizer->text($input->get->mac);
        if(isset($input->get->key)) $session->key = strtoupper($sanitizer->text($input->get->key));
        $content = renderPage('node_registration');
      } else {
        //  Register Node
        $content = registerNode($input->post->mac, $input->post->key);
        $content = "<h2>Node Hinzugefügt</h2><ul>$content</ul>";
      }
      break;
      case 'keys':
          //if(!autorized($input->secret)) throw new Wire404Exception();
          $useMain = false;
          $nodes = $pages->find("template=node, key!=''");
          $router_new = array();
          $router = array();
          $router_old = file_get_contents("http://register.freifunk-myk.de/srvapi.php");
          $router_old = unserialize($router_old);

          foreach($nodes as $node){
                $router_new[] = array('MAC' => "$node->title",
                                  'PublicKey' => strtoupper($node->key));
          }

          $list = array_merge($router_old, $router_new);
          $router = array_map("unserialize", array_unique(array_map("serialize", $list)));

          echo serialize($router);
        break;
        case 'import':
          if(!wire('user')->isLoggedin()){
            $content = "<article><h2>Gesicherte Seite</h2>Bitte Anmelden oder Registrieren.</article>";
          } elseif (!wire('user')->authsuccess) {
            $content = "<article><h2>Authorisiere deinen Account</h2><p>Um deine Nodes zu importieren musst du deine E-Mail Adresse verifizieren.</p></article>";
          } else {
            $query = new mysqlMigrate();
            $nodes = $query->searchNodes(wire('user')->email);
            if(empty($nodes)) {
              $content= "<article>
                        <h2>Keine Nodes gefunden</h2>
                        <p>Es konnten keine Nodes gefunden werden.
                        Die Nodes werden mit Hilfe deiner E-Mail Adresse gesucht.
                        Bitte überprüfe das deine E-Mail Adresse die selbe wie
                        im alten System ist. Sollten weiterhin Probleme sein
                        dann sprich einfach einen der Administratoren an.</p>
                        </article>";
              break;
            }
            foreach($nodes as $node){
              $content .= registerNode($node['MAC'], $node['PublicKey']);
            }
            $content = "<h2>Nodes Hinzufügen</h2><ul>$content</ul>";
          }
        break;
    default:
      throw new Wire404Exception();
  }

} else {
  $user = wire('user')->id;
  $nodes = $pages->find("operator=$user, template=node, sort=-subtitle");
  $table = '';

  foreach($nodes as $node){

    $table .="<tr class='".($node->online == 1 ? "alert success" : "alert danger")."'>
              <td>$node->subtitle</td>
              <td>$node->title</td>
              <td>$node->latitude</td>
              <td>$node->longitude</td>
              <td>".($node->online == 1 ? "online" : "offline")."</td>
              <td>{$node->operator->name}</td>
            </tr>";
  }

  $page->table = $table;
  $content = renderPage();
}
