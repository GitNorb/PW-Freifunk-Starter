<?php
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
