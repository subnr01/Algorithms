<?php header('Content-Type: application/json');
/*
 * Following code will list all the restaurant types
 */
 
// array for JSON response
$response = array();

// include db connect class
require_once('connection.php');

$result = mysql_query("SELECT DISTINCT type FROM `Restaurant`") or die(mysql_error());

// check for empty result
if (mysql_num_rows($result) > 0) {
	// looping through all results
    // root node
    $response["restaurant"] = array();
	
	while ($row = mysql_fetch_array($result)) {
        // temp user array
        $restaurant = array();
        $restaurant["type"] = $row["type"];
        // push single product into final response array
        array_push($response["restaurant"], $restaurant);
        }
        // success

        $response["success"] = 1;

        // echoing JSON response
        echo json_encode($response);
} else {
    // no restaurants found
    $response["success"] = 0;
    $response["message"] = "No Restaurant found";

    // echo no users JSON
    echo json_encode($response);
}

?>