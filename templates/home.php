<?php


// Imageslider mit der Bildbeschreibung als Titel
if(count($page->slider)){
  $slides = '';
  foreach($page->slider as $slide){
    $description = (!empty($slide->description) ? '<h2><span>'.$slide->description.'</span></h2>' : "");
    $slides .= "<li>
                <div class='slider-image'>
                  <img class='img-responsive' src='{$slide->size(1200,675)->url}'></img>
                  <h2><span>{$slide->description}</span></h2>
                </div>
              </li>";
  }
  $page->slides = $slides;
}


$content = renderPage();
