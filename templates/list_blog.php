<?php

$output_posts = '';

$posts = $pages->find("template=post,sort=-date");

foreach($posts as $post){


  $template = new TemplateFile($config->paths->templates . "markup/post_small.inc");
  $template->set('title', $post->title);
  $template->set('date', $post->getUnformatted('date'));
  $template->set('url', $post->httpUrl);
  $template->set('image', (count($post->images) ? "<img class='responsive' src='{$post->images->first()->size(300,200)->url}'></img>" : ""));
  $template->set('body', $post->get('summary|body'));
  $template->set('id', $post->id);

  $output_posts .= $template->render();

};

$template = new TemplateFile($config->paths->templates . "markup/list_blog.inc");
$template-> set('posts', $output_posts);

$content = $template->render();
