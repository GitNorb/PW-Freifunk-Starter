<?php
function makeTable(PageArray $pages, $tableArray, $status = false){
  $tableHead = '';
  $tableBody = '';

  // Head
  foreach($tableArray as $key => $value){
    $tableHead .= "<th>$key</th>";
  }

  // Body
  foreach($pages as $p){
    $tableBody .= ($status ? "<tr class='".($p->online == 1 ? "alert success" : "alert danger")."'>" : "<tr>") ;
    foreach($tableArray as $value){
      $tableBody .= "<td>{$p->get($value)}</td>";
    }
    $tableBody .= "</tr>";
  }

  // Structur
  $table = "<table>
              <thead>
                <tr>
                $tableHead
                </tr>
              </thead>
                <tbody>
                $tableBody
                </tbody>
              </table>";

  return $table;
}

#if($input->urlSegment3) throw new Wire404Exception();
$u = $users->get("name={$input->urlSegment1}");
$page->title = "{$page->title} {$u->name}";
$page->userID = $u->id;

if($user instanceof NullPage) throw new Wire404Exception();

// Nodes
$page->nodes = $pages->find("template=node, operator={$u->id}");

// IPs
$page->ips = $pages->find("template=staticip, operator={$u->id}");

$userlist = $users->find("start=0");
foreach($userlist as $uli){
  $liste .= "<li><a href='{$pages->get('/profile/')->httpUrl}{$uli->name}'>$uli->name</a></li>";
}
$page->userlist = "<ul>$liste</ul>";

$content = ($user->id === $u->id ? renderPage('profile_private') : renderPage());
