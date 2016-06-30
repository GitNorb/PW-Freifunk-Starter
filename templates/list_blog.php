<?php

$output = '';

$posts = $pages->find("template=post,sort=-date");

foreach($posts as $post){
  $image = (count($post->images) ? "<img class='responsive' src='{$post->images->first()->size(300,200)->url}'></img>" : "");

  $output .= "<article id='article-{$post->id}' class='row article'>
                <div class='medium-3 columns'>
                  $image
                </div>
                <div class='medium-9 columns'>
                  <h4 class='tobheader'><small>". strftime('%d %b %Y', $post->getUnformatted('date')) ."</small></h4>
                  <a href='{$post->httpUrl}'><h3>{$post->title}</h3></a>
                  <p>
                      {$post->get('body|summary')}
                  </p>
                </div>
            </article><!-- #article-7 -->
            <hr>";
};

$content = "<div id='article' class='blog-list large-9 columns'>
              $output
            </div><!-- #article -->
            <div id='sidebar' class='large-3 columns'>
              <h5>Neueste Router</h5>
              <ul>
                <li>Koblenz, Marktplatz</li>
                <li>Koblenz, Marktplatz</li>
                <li>Koblenz, Marktplatz</li>
                <li>Koblenz, Marktplatz</li>
                <li>Koblenz, Marktplatz</li>
              </ul>
            </div>";
