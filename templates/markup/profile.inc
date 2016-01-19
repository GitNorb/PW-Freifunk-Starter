<article id='article' class='medium-9 small-12 columns'>
  <h1><?=$page->title?></h1>

  <h2>Nodes <?php if($page->userID == $user->id){?><a title="Node hinzufügen" href="<?=$pages->get('/node/')->httpUrl?>add"><i class='fa fa-plus-circle'></i></a><?php }; ?></h2>
  <?php if ($page->nodes != false){ ?>
  <table>
    <thead>
      <tr>
        <th>Name</th>
        <th>MAC</th>
        <th>Latitude</th>
        <th>Longitude</th>
        <th>Status</th>
      </tr>
    <tbody>
      <?=$page->nodes?>
    </tbody>
  </table>
  <?php } elseif($page->userID == $user->id) { ?>
    <p>
      Du hast derzeit noch keine Nodes. Du kannst einen Node <a href="<?=$pages->get("/node/")->httpUrl?>add">eintragen</a>.
    </p>
  <?php } else { ?>
      <p>
        <?=$users->get($page->userID)->name?> betreibt aktuell noch keine eigenen Nodes.
      </p>
  <?php } ?>

  <h2>Statische IPs <?php if($page->userID == $user->id){ ?><a title="Service registrieren" href="<?=$pages->get('/service/')->httpUrl?>add"><i class='fa fa-plus-circle'></i></a> <?php }; ?></h2>
  <?php if ($page->nodes != false){ ?>
  <table class='node-list'>
    <thead>
      <tr>
        <th>Name</th>
        <th>MAC</th>
        <th>IP</th>
      </tr>
    </thead>
    <tbody>
      <?=$page->ips?>
    </tbody>
  </table>
  <?php } elseif($page->userID == $user->id) { ?>
    <p>
      Derzeit sind keine Services eingetragen. Du kannst einen Service <a href="<?=$pages->get("/static-ip/")->httpUrl?>add">registrieren</a>.
    </p>
  <?php } else { ?>
      <p>
        <?=$users->get($page->userID)->name?> betreibt aktuell noch keine eigenen Dienste.
      </p>
  <?php } ?>

</article>
<div id="sidebar" class="medium-3 small-12 columns">
  <?=$page->userlist?>
</div>
