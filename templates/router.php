<?php

$companyRouter = strtolower($page->parent->title) ."-". strtolower($page->title);
$page->set('stable', json_decode(file_get_contents("http://firmware.freifunk-myk.de/.static/filter/?filter={$companyRouter}&branch[]=stable&output=json")));
$page->set('beta', json_decode(file_get_contents("http://firmware.freifunk-myk.de/.static/filter/?filter=$companyRouter&branch[]=beta&output=json")));


$stableSysupgrade = "";
$stableFactory = "";
$betaFactory = "";
$betaSysupgrade = "";
foreach ($page->stable as $firmware) {
  $template = new TemplateFile($config->paths->templates . "markup/table_router_firmware.inc");
  $template->set('version', $firmware->version);
  $template->set('builddate', $firmware->builddate);
  $template->set('release', $firmware->release);
  $template->set('hash', ($firmware->hash ? $firmware->hash->md5 : ""));
  $template->set('filename', $firmware->filename);
  $template->set('url', "#");

  if($firmware->sysupgrade){
    $stableSysupgrade .= $template->render();
  } else {
    $stableFactory .= $template->render();
  };
}
foreach ($page->beta as $firmware) {
  $template = new TemplateFile($config->paths->templates . "markup/table_router_firmware.inc");
  $template->set('version', $firmware->version);
  $template->set('builddate', $firmware->builddate);
  $template->set('release', $firmware->release);
  $template->set('hash', ($firmware->hash ? $firmware->hash->md5 : ""));
  $template->set('filename', $firmware->filename);
  $template->set('url', "#");

  if($firmware->sysupgrade){
    $betaSysupgrade .= $template->render();
  } else {
    $betaFactory .= $template->render();
  };
}

$page->set('stableSysupgrade', $stableSysupgrade);
$page->set('stableFactory', $stableFactory);
$page->set('betaSysupgrade', $betaSysupgrade);
$page->set('betaFactory', $betaSysupgrade);

$content = renderPage();
