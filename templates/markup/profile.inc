<article id='article' class='medium-9 small-12 columns'>
  <h1><?=$page->title?></h1>

  <h2>Nodes</h2>
  <?php if ($page->nodes != false){ ?>
      <?=$page->nodes?>
  <?php } else { ?>
      <p>
        <?=$users->get($page->userID)->name?> betreibt aktuell noch keine eigenen Nodes.
      </p>
  <?php } ?>

  <h2>Statische IPs</h2>
  <?php if ($page->nodes != false){ ?>
      <?=$page->ips?>
  <?php } else { ?>
      <p>
        <?=$users->get($page->userID)->name?> betreibt aktuell noch keine eigenen Dienste.
      </p>
  <?php } ?>

</article>
<div id="sidebar" class="medium-3 small-12 columns">
  <?=$page->userlist?>
</div>
