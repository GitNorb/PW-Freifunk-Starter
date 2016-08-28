<article id='article' class='medium-9 small-12 columns'>
  <h1>Password zurücksetzen</h1>

  <form action='./pwreset' id="form_2" method="post">
    <label for="email">E-Mail</label>
    <input type="text" id="email" maxlength="40">
    <button type="submit">Password Zurücksetzen</button>
  </form>

</article>
<aside id="sidebar" class="medium-3 small-12 columns">
  <?=$page->userlist?>
</aside>
