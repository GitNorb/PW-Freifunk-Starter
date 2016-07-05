<?php

$nodeinfo = wire('modules')->get('NodeInfoUpdater');
$nodeinfo->set_nodeinfo(new HookEvent);

$content = renderPage();
