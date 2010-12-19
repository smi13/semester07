<?php
    $link = mysql_connect("localhost", "root", "12345") or die("Could not connect");
    if( !$link ) die( mysql_error() );

    $usertable = "minibuses";

    mysql_select_db("minibuses_db", $link);

    $query = "SELECT * FROM $usertable";

    $res = mysql_query($query) or die(mysql_error());

    $row = mysql_fetch_array($res);

    $num = $row['name'];

    while ($row = mysql_fetch_array($res)) {
        $num = $num . "," . $row['name'];
    }
    
    mysql_free_result($res);
    
    echo json_encode(array("result" => $num));
?>
