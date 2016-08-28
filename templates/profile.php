<?php
function makeTable(PageArray $pages, $tableArray, $status = false){
  $tableHead = '';
  $tableBody = '';

  // Head
  foreach($tableArray as $key => $value){
    $tableHead .= "<th>$key</th>";
  }

  // Body
  foreach($pages as $p){
    $tableBody .= ($status ? "<tr class='".($p->online == 1 ? "alert success" : "alert danger")."'>" : "<tr>") ;
    foreach($tableArray as $value){
      $tableBody .= "<td>{$p->get($value)}</td>";
    }
    $tableBody .= "</tr>";
  }

  // Structur
  $table = "<table>
              <thead>
                <tr>
                $tableHead
                </tr>
              </thead>
                <tbody>
                $tableBody
                </tbody>
              </table>";

  return $table;
}

// Nur eingeloggte User können Benutzerkonten ansehen
if(!wire('user')->isLoggedin()) throw new Wire404Exception();

// Password reset funktion
if($input->urlSegment1 == "pwreset") {

  if($input->post->token && $sanitizer->name($input->post->token) == $wire->user->get($sanitizer->name($input->post->user))->authkey){
    $t = new TemplateFile($config->paths->templates ."markup/passwordreset.inc");
  } else {
    $t = new TemplateFile($config->paths->templates ."markup/passwordreset_request.inc");
  }

  $content = $t->render();

  // Nach dem Speichern eines Formulars
  if($input->post->submit || $input->get->submit){

      // Wenn ein neues Password gesetzt wurde
      if($input->get->newpassword){
        $ldapuser['username'] = $input->post->user;
        $ldapuser['newPassword'] = $input->get->newpassword;
        if($ldap->save($ldapuser)){
          $content = "Password gespeichert, du kannst dich nun einloggen.";
        } else {
          $content = "Es ist ein fehler aufgetreten, versuche es zu einem Späteren Zeitpunkt noch einmal!";
        }
      }

      // Wenn ein Request gesendet wird
      if($input->post->email){
        $email = $sanitizer->email($input->post->email);
        $u = wire('users')->get("email=$email");

        $u->of(false);
        $u->authkey = getToken();
        $u->save();
        $u->of(true);

        $reseturl = wire('page')->httpUrl ."?token=". $u->authkey ."&user=". $u->name;
        $mail = wireMail();
        $mail->to($u->email)->from('reset@ffmyk.de');
        $mail->subject("Reset Password");
        $mail->body("===== Password Zurücksetzen ===== \n\n
        mit dieser E-Mail kannst du dein Password zurücksetzen.\n
        $reseturl \n
        Sollte der Link nicht anklickbar sein, kopiere ihn und füge ihn in die Adresszeile deines Browsers ein.");
        if($mail->send()) wire('log')->message('Send Mail: Account Aktivierung') ;

        $content = "Du erhälst eine E-Mail mit einem Link, falls keine E-Mail ankommt versuche es später noch einmal.";
      }
    }
}

// Wenn inputsegment 1 nicht gesetzt ist dann leite auf den aktuellen Benutzer weiter.
if(!$input->urlSegment1) $session->redirect("{$pages->get('/profile/')->url}{$user->name}");


if($input->urlSegment2 == "edit"){
  if($input->urlSegment1 != $user->name) $session->redirect("{$pages->get('/profile/')->url}{$user->name}/edit");
  // Get User Objekt from current User
  $u = $users->get("name={$user->name}");

  $t = new TemplateFile($config->paths->templates ."markup/profile_edit.inc");
  $t->set('firstname', $u->firstname);
  $t->set('lastname', $u->lastname);
  $t->set('email', $u->email);
  $t->set('publicKey', $u->public_key);

  $content = $t->render();
} else {

  #if($input->urlSegment3) throw new Wire404Exception();
  $u = $users->get("name={$sanitizer->name($input->urlSegment1)}");
  $page->title = "{$page->title} {$u->name}";
  $page->userID = $u->id;

  if($user instanceof NullPage) throw new Wire404Exception();

  // Nodes
  $page->nodes = $pages->find("template=node, operator={$u->id}");

  // IPs
  $page->ips = $pages->find("template=staticip, operator={$u->id}");

  $liste = "";
  $userlist = $users->find("start=0, name!='guest'");
  foreach($userlist as $uli){
    $liste .= "<li><a href='{$pages->get('/profile/')->httpUrl}{$uli->name}'>$uli->name</a></li>";
  }
  $page->userlist = "<ul>$liste</ul>";

  if(empty($content)) $content = ($user->id === $u->id ? renderPage('profile_private') : renderPage());

}
