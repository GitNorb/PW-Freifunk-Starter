<?php
/***************************************************************************************
 * _functions.inc
 *
 * The following defined here so that they can be used by multiple template files.
 * This file contains various "render" functions that generate markups specific
 * to the site profile (theme).
 *
 * What's Here:
 *
 * getTag() - Render a Tag List.
 * renderOnPageBlocks() - Render on-page blocks.
 * renderInfoBlocks() - Render Info blocks.
 * renderCopyrights(Page $page) - Render site copyrights content
 * getReferences() - Render testimonial/references
 * renderSidebar() - Return sidebar item as html markup
 * renderGoogleLocationMap() - Render google map locations
 * getContactUsForm() - Render contact form
 *
 *
 */

 /**
  * renderCopyrights(Page $page) - Render site copyrights content
  * You can find site copyrights content under Admin > Pages > Home edit page and find Global site settings.
  *
  * @param Page $page - instance of the page.
  * @return String - html markup string of copyright statement
  */

#########################################################
# getter
#########################################################
 /**
  * getTag()
  *
  * @param  PageArray $tags - instance of PageArray
  * @param  int $limit - limit of the output
  * @return string - html markup string of Tag list elements.
  */
function getTag(PageArray $tags, $limit = 0){
  $list = "";
  $count = "0";
  foreach($tags as $tag){
    $count++;
    if($count > $limit && $limit != 0) break;
    $title = $tag->title;
    $list .= "<li>$title</li>";
  }
  return $list;
}

#########################################################
# setter
#########################################################
function setNodeInfo(){
  $file = file_get_contents('http://ffmyk.niyawe.de/status/data/nodelist.json');

  $data = json_decode($file, true);

  foreach($data['nodes'] as $node){
    $title = preg_replace('/(.{2})(.{2})(.{2})(.{2})(.{2})(.{2})/', "$1-$2-$3-$4-$5-$6", $node['id']);
    $p = wire('pages')->get("template=node, title|name=$title");

    if($p instanceof NullPage) continue;

    $p->of(false);
    $p->subtitle = $node['name'];
    $p->latitude = $node['position']['lat'];
    $p->longitude = $node['position']['long'];
    $p->online = $node['status']['online'];
    $p->lastconnection = strtotime($node['status']['lastcontact']);
    $p->save();
    $p->of(true);
  }
}

###################################################
# Render
####################################################
function renderCopyrights(Page $page) {

    if (!$page->summary) return '';

    $text = str_replace(
        // find these:
        array('{year}'),
        // and replace with these:
        array(date('Y')),
        // in the copyright_text text
        $page->summary);

    return $text;
}

function renderTimeline($timeline){
  // Überprüfe ob $timeline von der richtigen Instants ist
  if(!$timeline instanceof PageArray) {
    if($timeline instanceof Page){
      //single page
      $post = $timeline;
      $timeline = new PageArray();
      $timeline->add($post);
    } else if(is_string($timeline)) {
      // selector string
      $selector = $timeline;
      $timeline = wire('pages')->find("template=post, sort=-date, $selector");
    } else {
      throw new WireException('getTimeline requires a PageArray, Page or selector string');
    }
  }


  // Count for the while Schleife
  $count = 0;
  $output = '';

  foreach($timeline as $post){
    $title = $post->date;
    $subheading = $post->title;
    $summary = $post->summary;
    $image = $post->images->first();
    $readmore = $post->httpUrl;
    $leftright = ($count % 2 != 0 ? "" : "class='timeline-inverted'");

    $output .= "<li $leftright>
                  <div class='timeline-image'>
                    <img class='img-circle img-responsive' src='{$image->size(156,156)->url}' alt='{$image->description}'>
                  </div>
                  <div class='timeline-panel'>
                    <div class='timeline-heading'>
                      <h4>$title</h4>
                      <h4 class='subheading'>$subheading</h4>
                    </div>
                    <div class='timeline-body'>
                      <p class='text-muted'>
                        $summary <a href='{$readmore}'>Weiterlesen</a>
                      </p>
                    </div>
                  </div>
                </li>";

      $count++;
  }

  return  "<section id='timeline' data-magellan-destination='timeline' class='info container'>
                <div class='row'>
                  <div class='columns large-12 text-center'>
                    <h2 class='section-heading'>Timeline</h2>
                    <h3 class='subheader'><small>Unser Weg zum freien Netz.</small></h3>
                  </div>
                </div>
                <div class='row'>
                  <div class='large-12 columns'>
                    <ul class='timeline'>
                      $output
                      <li class='timeline-inverted'>
                        <div class='timeline-image'>
                          <h4>Werde
                            <br>Teil unserer
                            <br>Community!</h4>
                          </div>
                        </li>
                      </ul><!-- #timelines -->
                    </div>
                  </div>
                </div>
              </section><!-- #timeline -->";

}

/* Vorbereitung für Landingpages einzelner Communitys */
function renderOnPageBlocks() {

    // Get the current page instance from global scope.
    $page = wire('page');
    // Get the config instance from global scope.
    $config = wire('config');

    if (!count($page->on_page_blocks)) return '';

    /* Get on-page blocks */
    $pageBlocks = $page->on_page_blocks;

    $out = '';

    foreach ($pageBlocks as $block) {

        //Create delegate template
        $template = new TemplateFile($config->paths->templates . "markup/page-block-type-{$block->render_option}.inc");
        //Assign the rendered view to content variable to show up on page-block-type-x.inc
        $template->set('image', $block->image);

        $content = str_replace(
            // find these:
            array('<ul>','<!-- pagebreak -->'),
            // and replace with these:
            array('<ul class="default-list-square">', '<br/>'),
            // in the $block->body text
            $block->body
        );

        //Assign the rendered view to content variables to show up on page-block-type-x.inc
        $template->set('content', $content);
        $template->set('headline', $block->get('headline|title'));

        //Get the output and save it on $out.
        $out .= $template->render();
    }

    return $out;
}

function renderPage($template = "") {
  if(empty($template)) $template = wire('page')->template;
  $config = wire('config');

  //Create delegate template
  $template = new TemplateFile($config->paths->templates . "markup/$template.inc");

  //Get the output and save it on $out.
  return $template->render();
}

/* Rendern der Infoblocks von Router */
function renderInfoBlocks() {

    // Get the current page instance from global scope.
    $page = wire('page');
    // Get the config instance from global scope.
    $config = wire('config');

    if (!count($page->info_blocks)) return '';

    /* Get Info blocks */
    $infoBlocks = $page->info_blocks;

    $out = '';

    foreach ($infoBlocks as $block) {

        //Create delegate template
        $template = new TemplateFile($config->paths->templates . "markup/info-block.inc");

        $content = str_replace(
            // find these:
            array('<ul>','<!-- pagebreak -->'),
            // and replace with these:
            array('<ul class="default-list-square">', '<br/>'),
            // in the $block->body text
            $block->body
        );

        //Assign the rendered view to content variables to show up on page-block-type-x.inc
        $template->set('content', $content);
        $template->set('headline', $block->get('title'));

        //Get the output and save it on $out.
        $out .= $template->render();
    }

    return $out;
}

function renderSidebarFilter(){
  $hersteller = listPages(wire('pages')->find("template=hersteller"));
  $features = listPages(wire('pages')->find("template=features"));

  $output = "<div id='sidebar' class='large-2 columns'>
                <h3>Filter</h3>
                <h5>Hersteller</h5>
                <ul class='filter'>
                  $hersteller
                </ul>

                <h5>Features</h5>
                <ul class='filter'>
                  $features
                </ul>
              </div><!-- #sidebar-->";

  return $output;
}

// Render a Page Title
function renderPageName($title){
	$sanitizer = wire('sanitizer');
	$string = iconv("UTF-8", "ASCII//TRANSLIT", $title);
	$string = preg_replace("/\s+/", " ", $string);  // Überflüssige Leerzeichen entfernen
	$string = trim($string); // Leerzeichen am Anfang und Ende entfernen
	$string = $sanitizer->pageName($string);

	return $string;
}


##########################################################
# Sonstiges
#########################################################
function listPages(PageArray $pages){
  $output = "";
  foreach($pages as $page){
    $output .= "<li><a href='{$page->httpUrl}'>{$page->title}</a></li>";
  }
  return $output;
}


/**
 * Function to Create Processwire Pages
 *
 * @param  string $template     the template for the new page
 * @param  Page/string $parent  parent Page can be a Page or string
 * @param  string $title        Title of the new Page
 * @return PageArray            The new Page
 */
function createPage($template, $parent, $title){
	if(!$parent instanceof Page) $parent = wire('pages')->get("/$parent/"); // Wenn keine Seite übergeben wird suche eine raus.

	$pageName = renderPageName($title);

	$t = new Page();
	$t->template = $template;
	$t->parent = $parent;
	$t->name = $pageName;
	$t->title = $title;
	$t->save();

	return $t;
}

/**
 * Fucntion to handle Node registration
 *
 * @param string $mac     the MAC Address from the Node
 * @param string $key     the Node PublicKey for the VPN connection_status
 * @return string         the Output String to Display the Information of register Node
 */
function registerNode($mac, $key){
  if(empty($mac) || empty($key)) return;

  $page = wire('page');
  $node = wire('pages')->get("template=node, title=$mac");
  $parent = wire('pages')->get($page->id);
  $operator = wire('user')->id;

  // Check some part of node
  if($node instanceof Nullpage){
    $titlemac = strtoupper($mac);
    $n = createPage('node', $parent, $titlemac);
    $title = "<h2>Node hinzugefügt:</h2>";
  } elseif($node->operator->id != $operator) {
    // Checke ob der Node vom Besitzer geändert wird.
    $content = "<h2>Node nicht Hinzugefügt</h2>
                <p>
                Der Node ist auf einen anderen User registriert. Um ihn registrieren zu können muss der alte Besitzer den Node aus seinem Profil löschen.
                </p>";
    return $content;
  } else {
    $n = $node;
    $title = "<h2>Node aktualisiert:</h2>";
  }

  $n->key = $key;
  $n->operator = $operator;
  $n->of(false);
  $n->save();
  $n->of(true);

  $content = "$title
              <p>
              Titel: {$n->title}<br>
              Key : {$n->key}<br>
              Betreiber: {$n->operator->name}
              </p>";

  wire('session')->remove('key');
  wire('session')->remove('mac');

  return $content;
}
#################################################
# secret
#################################################
function autorized($secret){
  $pages = wire('pages');
  $secrets = $pages->get("secret=$secret, template=supernode");
  if($secrets instanceof NullPage) return false;
  return true;
}

#################################################
# Hooks
#################################################

wire()->addHook('LazyCron::every2Minutes', null, 'setNodeInfo');

class jsonparser {
        private $src = 'http://status.freifunk-myk.de/nodedata/nodes.json';

        private $cache = false;
        private $cache_node = array();

        function __construct() {
            $htmlcache = file_get_contents($this->src);
            $this->cache = json_decode($htmlcache);
            $this->gen_nodecache();
        }

        function gen_nodecache() {
            foreach($this->cache->nodes as $node) {
                $this->cache_node[base64_encode(strtoupper($node->nodeinfo->node_id))] = $node;
            }
            $this->cache=false;
        }

        function get_nodeinfo($mac) {
            $mac = strtoupper(str_replace(':', '', $mac));
            $data = array(
                'addresses' => array(''),
                'hardware' => 'unbekannt',
                'firmware' => 'unbekannt',
                //'autoupdater_state' => false,
                'name' => 'unbekannt',
                'lastseen' => 0,
                'geo' => array(0,0),
                'ip' => ''
            );

            if(!isset($this->cache_node[base64_encode($mac)])) return $data;
            $info = $this->cache_node[base64_encode($mac)];

            $ip = '';
            if(isset($info->nodeinfo->network->addresses)) {
                foreach($info->nodeinfo->network->addresses as $tip) {
                    if(substr($tip, 0, 4) == '2a01') $ip = $tip;
                }
            }

            $data = array(
                'addresses' => $info->nodeinfo->network->addresses,
                'hardware' => $info->nodeinfo->hardware->model,
                'firmware' => $info->nodeinfo->software->firmware->release,
                'autoupdater_state' => $info->nodeinfo->software->autoupdater->enabled,
                'name' => $info->nodeinfo->hostname,
                'lastseen' => $info->lastseen,
                'geo' => $info->nodeinfo->location,
                'ip' => $ip
            );
            return $data;
        }
    }
