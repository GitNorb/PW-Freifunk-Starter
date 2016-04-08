<?php
// Wenn inputsegment 1 nicht gesetzt ist dann leite auf den aktuellen Benutzer weiter.
if(!wire('user')->isLoggedin()) throw new Wire404Exception();

if(!$input->urlSegment1) $session->redirect("{$pages->get('/profile/')->url}{$user->name}");                                                                                                     │·················


#if($input->urlSegment3) throw new Wire404Exception();
$u = $users->get("name={$sanitizer->name($input->urlSegment1)}");
$page->title = "{$page->title} {$u->name}";
$page->userID = $u->id;

if($user instanceof NullPage) throw new Wire404Exception();

// Nodes
$page->nodes = $pages->find("template=node, operator={$u->id}");

// IPs
$page->ips = $pages->find("template=staticip, operator={$u->id}");


$content = ($user->id === $u->id ? renderPage('profile_private') : renderPage());
