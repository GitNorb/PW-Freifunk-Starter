<?php

#if($input->urlSegment3) throw new Wire404Exception();
$u = $users->get("name={$input->urlSegment1}");
$page->title = "{$page->title} {$u->name}";
$page->userID = $u->id;

if($user instanceof NullPage) throw new Wire404Exception();

$nodes = $pages->find("template=node, operator={$u->id}");
foreach($nodes as $node){

  $status = ($node->online == 1 ? "alert success" : "alert danger");
  $online = ($node->online == 1 ? "online" : "offline");
  $table_nodes .="<tr class='$status'>
            <td>$node->subtitle</td>
            <td>$node->title</td>
            <td>$node->latitude</td>
            <td>$node->longitude</td>
            <td>$online</td>
          </tr>";
}
$page->nodes = ( empty($nodes) ? false : $table_nodes );


$services = $pages->find("template=service, operator={$u->id}");
foreach($services as $service){
  if(empty($service->static_ip)) $service->static_ip = "in Bearbeitung";
  $table_service .="<tr class='$status'>
            <td>$service->subtitle</td>
            <td>$service->title</td>
            <td>$service->static_ip</td>
          </tr>";
}
$page->services = ( empty($services) ? false : $table_service );

$userlist = $users->find("start=0");
foreach($userlist as $uli){
  $liste .= "<li><a href='{$pages->get('/profile/')->httpUrl}{$uli->name}'>$uli->name</a></li>";
}
$page->userlist = "<ul>$liste</ul>";

$content = renderPage();
