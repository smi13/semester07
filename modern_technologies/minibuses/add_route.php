<?php
    $route = $_GET[var1];
    $name = $_GET[var2];

    $link = mysql_connect("localhost", "root","12345") or die("Could not connect");
    $usertable = "minibuses";
    if( !$link ) die( mysql_error() );

    mysql_select_db("minibuses_db", $link);

    $query = "INSERT INTO $usertable (name, route) VALUES ( '$name' , '$route')";

    $res = mysql_query($query) or die(mysql_error());

    echo $route;
    echo $name;
?>