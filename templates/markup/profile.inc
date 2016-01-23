<article id='article' class='medium-9 small-12 columns'>
  <h1><?=$page->title?></h1>

  <h2>Nodes</h2>
  <?php
  if(!count($page->nodes)){
      echo "<p>{$users->get($page->userID)->name} betreibt aktuell noch keine eigenen Nodes.</p>";
    } else {
      echo makeTable($page->nodes, array("Name"  => "subtitle",
                                          "MAC"   => "title",
                                          "Latitude" => "latitude",
                                          "Longitude" => "longitude",
                                          "Status" => "online"), true);
    }
    ?>

  <h2>Statische IPs</h2>
  <?php
  if(!count($page->ips)){
    echo "{$users->get($page->userID)->name} betreibt aktuell noch keine eigenen Dienste.";
  } else {
    echo makeTable($page->ips, array("Bezeichnung" => "subtitle",
                                "MAC" => "title",
                                "IP" => "static_ip"));
  }
  ?>

</article>
<div id="sidebar" class="medium-3 small-12 columns">
  <?=$page->userlist?>
</div>
