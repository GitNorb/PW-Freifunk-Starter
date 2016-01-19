<?php
function registerNode($mac, $key){
  if(empty($mac) || empty($key)) return;

  $page = wire('page');
  $node = wire('pages')->get("template=node, title=$mac");
  $parent = wire('pages')->get($page->id);
  $operator = wire('user')->id;

  // Check some part of node
  if($node instanceof Nullpage){
    $titlemac = strtoupper($mac);
    $n = createPage('node', $parent, $titlemac);
    $title = "<h2>Node hinzugefügt:</h2>";
  } elseif($node->operator->id != $operator) {
    // Checke ob der Node vom Besitzer geändert wird.
    $content = "<h2>Node nicht Hinzugefügt</h2>
                <p>
                Der Node ist auf einen anderen User registriert. Um ihn registrieren zu können muss der alte Besitzer den Node aus seinem Profil löschen.
                </p>";
    return $content;
  } else {
    $n = $node;
    $title = "<h2>Node aktualisiert:</h2>";
  }

  $n->key = $key;
  $n->operator = $operator;
  $n->of(false);
  $n->save();
  $n->of(true);

  $content = "$title
              <p>
              Titel: {$n->title}<br>
              Key : {$n->key}<br>
              Betreiber: {$n->operator->name}
              </p>";

  wire('session')->remove('key');
  wire('session')->remove('mac');

  return $content;
}

if($input->urlSegment2) throw new Wire404Exception();

if($input->urlSegment1){
  switch($input->urlSegment1){
    case 'list':
      $nodes = $pages->find('template=node, sort=-subtitle');
      $table = '';

      foreach($nodes as $node){

        $status = ($node->online == 1 ? "alert success" : "alert danger");
        $table .="<tr class='$status'>
                  <td>$node->subtitle</td>
                  <td>$node->title</td>
                  <td>$node->latitude</td>
                  <td>$node->longitude</td>
                  <td>$node->online</td>
                  <td>{$node->operator->name}</td>
                </tr>";
      }

      $page->table = $table;
      $content = renderPage();
      break;
    case 'map':
      break;
    case 'add':
      // Check if user is logged in and save the input->get in the session variable.
      if(!wire('user')->isLoggedin()){
        $content = "<article><h2>Gesicherte Seite</h2>Bitte Anmelden oder Registrieren.</article>";
        $session->redirectUrl = $page->path."add/";
        if(isset($input->get->mac)) $session->mac = $input->get->mac;
        if(isset($input->get->key)) $session->key = $input->get->key;
      } elseif(!$input->post->submit) {
        if(isset($input->get->mac)) $session->mac = $input->get->mac;
        if(isset($input->get->key)) $session->key = $input->get->key;
        $content = renderPage('node_registration');
      } else {
        //  Register Node
        $content = registerNode($input->post->mac, $input->post->key);
      }
      break;
      case 'keys':
          if(!autorized($input->secret)) throw new Wire404Exception();
          $useMain = false;
          $nodes = $pages->find("template=node, key!=''");
          $router = array();
          foreach($nodes as $node) {
              $router[] = array('MAC' => "{$node->title}",
                                'PublicKey' => "{$node->key}");
          }

          echo serialize($router);
        break;
    default:
      throw new Wire404Exception();
  }

} else {
  $user = wire('user')->id;
  $nodes = $pages->find("operator=$user, template=node, sort=-subtitle");
  $table = '';

  foreach($nodes as $node){

    $status = ($node->online == 1 ? "alert success" : "alert danger");
    $online = ($node->online == 1 ? "online" : "offline");
    $table .="<tr class='$status'>
              <td>$node->subtitle</td>
              <td>$node->title</td>
              <td>$node->latitude</td>
              <td>$node->longitude</td>
              <td>$online</td>
              <td>{$node->operator->name}</td>
            </tr>";
  }

  $page->table = $table;
  $content = renderPage();
}
