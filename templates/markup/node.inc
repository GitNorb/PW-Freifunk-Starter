<article id='article' class='large-9 columns'>
  <h1><?=$page->get('subtitle|title')?></h1>
  <table style="width:100%">
    <tr>
      <th>Name</th>
      <td><?=$page->subtitle?></td>
    </tr>
    <tr>
      <th>MAC</th>
      <td><?=$page->title?></td>
    </tr>
    <tr>
      <th>IPv6</th>
      <td><a href="http://[<?=$page->ipv6?>]/"><?=$page->ipv6?></a></td>
    </tr>
    <tr>
      <th>Hardware</th>
      <td><?=$page->node_hardware?></td>
    </tr>
    <tr>
      <th>Firmware</th>
      <td><?=$page->node_firmware?></td>
    </tr>
    <tr>
      <th>Status</th>
      <td><?=($page->online ? "<span style='color:green'>online</span>" : "<span style='color:red'>offline</span> $page->losttime")?></td>
    </tr>
    <tr>
      <th>Map</th>
      <td><a href='http://status.freifunk-myk.de/#!v:m;n:<?=strtolower(str_replace(":", "", $page->title))?>'><?=$page->address?></a></td>
    </tr>
  </table>
  <div id='map' style='width:100%; height:200px' class='map'></div>



</article><!-- #article -->
<aside id="sidebar" class="large-3 columns">
  <h4>Nodes in der Nähe (1km)</h4>
  <ul class='node-list'>
    <?php $nearnodes = umkreissuche("node", $page->latitude, $page->longitude, 1);
          foreach ($nearnodes as $node) { ?>
      <li>
        <i class='fa fa-wifi' style='color:<?=($node->online ? 'green' : 'red')?>'></i> <a href='<?=$node->httpUrl?>'><?=$node->get('subtitle|title')?> </a><br>
        <span class='node-address'><i class='fa fa-fw'></i> <?=getDistance($node->dist)?> entfernt</span>
      </li>
    <?php } ?>
  </ul>

  <?php echo renderNewNodesList(); ?>
</aside>
