<article id='article' class='medium-9 small-12 columns'>
  <h1><?=$page->title?></h1>

  <h2>Nodes</h2>
  <?php
  if(!count($page->nodes)){
    echo "<p>{$users->get($page->userID)->name} betreibt aktuell noch keine eigenen Nodes.</p>";
  } else { ?>
    <table class='node-list'>
      <thead>
        <tr>
          <th>Name</th>
          <th>MAC</th>
          <th>Latitude</th>
          <th>Longitude</th>
          <th>Status</th>
        </tr>
      </thead>
      <tbody>
        <?php
        foreach($page->nodes as $node){
          echo "<tr class='".($node->online == 1 ? "alert success" : "alert danger")."'>
          <td>$node->subtitle</td>
          <td>$node->title</td>
          <td>$node->latitude</td>
          <td>$node->longitude</td>
          <td>".($node->online == 1 ? "online" : "offline")."</td>
          </tr>";
        } ?>
      </tbody>
    </table>

  <?php } ?>


  <h2>Statische IPs</h2>
  <?php
  if(!count($page->ips)){
    echo "{$users->get($page->userID)->name} betreibt aktuell noch keine eigenen Dienste.";
  } else { ?>
    <table class='node-list'>
      <thead>
        <tr>
          <th>Name</th>
          <th>MAC</th>
          <th>IP</th>
        </tr>
      </thead>
      <tbody>
        <?php
        foreach($page->ips as $ip){
          echo "<tr class='".($node->online == 1 ? "alert success" : "alert danger")."'>
          <td>$ip->subtitle</td>
          <td>$ip->title</td>
          <td>$ip->static_ip</td>
          </tr>";
        } ?>
      </tbody>
    </table>
  <?php } ?>

</article>
<aside id="sidebar" class="medium-3 small-12 columns">
  <?=$page->userlist?>
</aside>
