<article id='article' class='medium-9 small-12 columns'>
  <h1><?=$page->title?></h1>

  <h2>Nodes <a title="Node hinzufügen" href="<?=$pages->get('/node/')->httpUrl?>add"><i class='fa fa-plus-circle'></i></a></h2>
  <?php
  if(!count($page->nodes)){
    echo "<p>Du hast derzeit noch keine Nodes. Du kannst einen Node über das <i class='fa fa-plus-circle'></i> Symbol eintragen.</p>";
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


  <h2>Statische IPs <a title="Service registrieren" href="<?=$pages->get('/service/')->httpUrl?>add"><i class='fa fa-plus-circle'></i></a> </h2>
  <?php
  if (!count($page->ips)){
    echo "<p>Derzeit hast du keine Statischen IPs angefordert. Du kannst welche anfordern über das <i class='fa fa-plus-circle'></i> Symbol.</p>";
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
