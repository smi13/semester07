<?php
    $link = mysql_connect("1", "1","1") or die("Could not connect");

    $route = mysql_real_escape_string($_POST['route']);
    $name = mysql_real_escape_string($_POST['name']);

    $usertable = "minibuses";
    if( !$link ) die( mysql_error() );

    mysql_select_db("minibuses_db", $link);

    $query = "INSERT INTO $usertable (name, route) VALUES ('$name', '$route')";

    $res = mysql_query($query) or die(mysql_error());    
?>