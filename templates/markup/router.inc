<article id='article' class='large-12 columns'>
  <div class='row'>
    <div class='large-9 columns'>
      <h1><?=$page->parent->title?> <?=$page->title?></h1>
      <p>
      <?=$page->body?>
      </p>
      <hr>
      <?=renderInfoBlocks();?>
      <h2>Firmware</h2>
      <p>
        Im Folgenden findest du die Firmware zum Router. Für den produktiven - also möglichst ausfallsicheren - Betrieb solltest du die Stable Firmware nutzen. Diese wird vor der Veröffentlichung getestet und enthält meistens keine Fehler mehr.
      </p>
      <ul class='accordion' data-accordion>
        <li class='accordion-navigation'>
          <a href='#stable'>Stable</a>
          <div id='stable' class='content'>
            Wenn du einen Router mit Originalfirmware hast oder dir nicht sicher bist was genau du brauchst dann nimm die Factory-Firmware. Um deinen Router mit Freifunk-Firmware zu aktualisieren kannst du Sysupgread benutzen.
            <h4><span data-tooltip aria-haspopup='true' class='has-tip' title='Möchtest du deinen Router zum Freifunk-Router umfunktionieren bist du hier richtig.'>Factory</span></h4>
            <table class='firmware-download-list'>
              <thead>
                <tr>
                  <th width='50'>Version/<br/>Modell</th>
                  <th width='50'>Datum</th>
                  <th width='50'>Release</th>
                  <th width='200'>MD5</th>
                  <th>Download</th>
                </tr>
              </thead>
              <tbody>
                <?=$page->stableFactory?>
              </tbody>
            </table><!-- table factory -->
            <h4><span data-tooltip aria-haspopup='true' class='has-tip' title='Möchtest du deinen Freifunk-Router Aktualisieren dann ist Sysupgread die richtige Wahl.'>Sysupgread</span></h4>
            <table class='firmware-download-list'>
              <thead>
                <tr>
                  <th width='50'>Version/<br/>Modell</th>
                  <th width='50'>Datum</th>
                  <th>Release</th>
                  <th>MD5</th>
                  <th>Download</th>
                </tr>
              </thead>
              <tbody>
                <?=$page->stableSysupgrade?>
              </tbody>
            </table><!-- table sysupgread -->
          </div><!-- #stable -->
        </li><!-- #accordion stable -->
        <li class='accordion-navigation'>
          <a href='#nightly'>Beta</a>
          <div id='nightly' class='content'>
            <h4>Factory</h4>
            <table class='firmware-download-list'>
              <thead>
                <tr>
                  <th width='50'>Version/<br/>Modell</th>
                  <th width='50'>Datum</th>
                  <th width='50'>Release</th>
                  <th width='200'>MD5</th>
                  <th>Download</th>
                </tr>
              </thead>
              <tbody>
                <?=$page->betaFactory?>
              </tbody>
            </table><!-- table fectory -->
            <h4>Sysupgread</h4>
            <table class='firmware-download-list'>
              <thead>
                <tr>
                  <th width='50'>Version/<br/>Modell</th>
                  <th width='50'>Datum</th>
                  <th width='50'>Release</th>
                  <th>MD5</th>
                  <th>Download</th>
                </tr>
              </thead>
              <tbody>
                <?=$page->betaSysupgrade?>
              </tbody>
            </table><!-- table sysupgread -->
          </div><!-- #nightly -->
        </li><!-- nightly -->
      </ul><!-- #arcordion -->
    </div><!-- #columns large-9 -->
    <div id='router-infobox' class='large-3 columns'>
      <div class='panel'>
        <img class='responsive' src='<?php echo (count($page->image) ? $page->image->first()->size(250,250)->url : 'https://placehold.it/250x250?text=No Image'); ?>'> </img>

        <hr>
        Hersteller: <a href='<?=$page->parent->website?>'><?=$page->parent->title?></a><br/>
        OpenWrt: <a href='https://wiki.openwrt.org/toh/<?=$page->parent->name?>/<?=$page->name?>"><?=$page->title?></a><br/>
        <hr>
        <h4>Features</h4>
        <ul class='features'>
          <?php echo getTag($page->features); ?>
        </ul>
      </div><!-- #panel -->
    </div><!-- #router-infobox -->
  </div><!-- #row -->
</article><!-- #article -->
