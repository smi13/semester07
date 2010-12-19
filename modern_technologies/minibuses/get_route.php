<?php
    $link = mysql_connect("1", "1", "1") or die("Could not connect");
    if( !$link ) die( mysql_error() );

    $name = mysql_real_escape_string($_GET['name']);

    $usertable = "minibuses";

    mysql_select_db("minibuses_db", $link);
    $query = "SELECT * FROM $usertable WHERE name='$name'";

    $res = mysql_query($query) or die(mysql_error());

    $row = mysql_fetch_array($res);

    $route = $row['route'];

    mysql_free_result($res);

    echo json_encode(array("result" => $route));
?>
