<?php
/******************
 * This File define the standart variables
 * used in main.inc.
 ******************/

//Steuert die Ausgabe von _main.inc, standart true gibt Main aus.
$useMain = true;
/**
 * Article variables
 **/
$headline = $page->get("headline|title");
$authorID = $page->createdUser;
$content = (!empty($page->body) ? $page->body : "");
$date = $page->created;
$url = $page->httpUrl;
$today = time();
$id = $page->id;
$title = $page->get("headline|title");
$fullwidth = false;

// set a couple new fields that our output will use
$page->set('authorURL', wire('config')->urls->root . 'profile/' . $page->createdUser->name . '/');
$page->set('authorName', wire('page')->createdUser->get('name|title') );

require_once("./_function.inc");
