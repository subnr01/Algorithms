<?php header('Content-Type: application/json');
/*
 * Following code will list all the manufacturers
 */
 
// array for JSON response
$response = array();

// include db connect class
require_once('connection.php');

// check for post data
if (isset($_POST["id"])) {
    $id = $_POST['id'];

	
	$result = mysql_query("DELETE FROM `Restaurant` WHERE `restaurantID`=$id") or die(mysql_error());
	
	// check if row deleted or not
    if (mysql_affected_rows() > 0) {
        // successfully updated
        $response["success"] = 1;
        $response["message"] = "Restaurant successfully deleted";
 
        // echoing JSON response
        echo json_encode($response);
    } else {
        // no product found
        $response["success"] = 0;
        $response["message"] = "No Restaurant found";
 
        // echo no users JSON
        echo json_encode($response);
    }
} else {
    // required field is missing
    $response["success"] = 0;
    $response["message"] = "Required field(s) is missing";
 
    // echoing JSON response
    echo json_encode($response);
}


?>