<?php header('Content-Type: application/json');
/*
 * Following code will list all the manufacturers
 */
 
// array for JSON response
$response = array();

// include db connect class
require_once('connection.php');

// check for post data
if (isset($_GET["id"])) {
    $id = $_GET['id'];

    
    // get all products from products table
    $result = mysql_query("SELECT * FROM `Restaurant` WHERE `restaurantID`=$id") or die(mysql_error());
	
	// check for empty result
	if (mysql_num_rows($result) > 0) {
		// looping through all results
	    // manufacturers node
	    $response["restaurant"] = array();
		
		while ($row = mysql_fetch_array($result)) {
	        $restaurant = array();
	        $restaurant["id"] = $row["restaurantID"];
	        $restaurant["name"] = $row["name"];
	        $restaurant["type"] = $row["type"];
	        $restaurant["bio"] = $row["bio"];
	        $restaurant["addressLine1"] = $row["addressLine1"];
	        $restaurant["addressLine2"] = $row["addressLine2"];
	        $restaurant["addressLine3"] = $row["addressLine3"];
	        $restaurant["contactNumber"] = $row["contactNumber"];
	        $restaurant["email"] = $row["email"];
	      	$restaurant["image"] = $row["image"];
	        $restaurant["lat"] = $row["lat"];
	        $restaurant["lng"] = $row["lng"];
	        $restaurant["url"] = $row["url"];

	        // push single product into final response array
	        array_push($response["restaurant"], $restaurant);
	        }
	        // success
	
	        $response["success"] = 1;
	
	        // echoing JSON response
	        echo json_encode($response);
	} else {
	    // no products found
	    $response["success"] = 0;
	    $response["message"] = "No Restaurant found";
	
	    // echo no users JSON
	    echo json_encode($response);
	}
}
else {
    // required field is missing
    $response["success"] = 0;
    $response["message"] = "Required field(s) is missing";

    // echoing JSON response
    echo json_encode($response);
}

?>