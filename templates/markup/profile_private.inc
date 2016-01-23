<article id='article' class='medium-9 small-12 columns'>
  <h1><?=$page->title?></h1>

  <h2>Nodes <a title="Node hinzufügen" href="<?=$pages->get('/node/')->httpUrl?>add"><i class='fa fa-plus-circle'></i></a></h2>
  <?php
  if(!count($page->nodes)){
      echo "<p>Du hast derzeit noch keine Nodes. Du kannst einen Node über das <i class='fa fa-plus-circle'></i> Symbol eintragen.</p>";
    } else {
      echo makeTable($page->nodes, array("Name"  => "subtitle",
                                          "MAC"   => "title",
                                          "Latitude" => "latitude",
                                          "Longitude" => "longitude",
                                          "Status" => "online") , true);
    }
    ?>


  <h2>Statische IPs <a title="Service registrieren" href="<?=$pages->get('/service/')->httpUrl?>add"><i class='fa fa-plus-circle'></i></a> </h2>
  <?php
  if (!count($page->ips)){
    echo "<p>Derzeit hast du keine Statischen IPs angefordert. Du kannst welche anfordern über das <i class='fa fa-plus-circle'></i> Symbol.</p>";
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
