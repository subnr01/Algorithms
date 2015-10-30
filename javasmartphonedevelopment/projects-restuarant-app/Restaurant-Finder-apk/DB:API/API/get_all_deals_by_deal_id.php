<?php header('Content-Type: application/json');
/*
 * Following code will list all the deals
 */
 
// array for JSON response
$response = array();

// include db connect class
require_once('connection.php');

// check for post data
if (isset($_GET["id"])) {
    $id = $_GET['id'];

// get all products from products table
$result = mysql_query("SELECT * FROM `Deals` WHERE `dealID`=".$id) or die(mysql_error());

// check for empty result
if (mysql_num_rows($result) > 0) {
	// looping through all results
    // manufacturers node
    $response["deals"] = array();
	
	while ($row = mysql_fetch_array($result)) {
        // temp user array
        $deal = array();
        $deal["id"] = $row["dealID"];
        $deal["dealName"] = $row["dealName"];
        $deal["price"] = $row["price"];
        $deal["description"] = $row["description"];
        $deal["restID"] = $row["restaurantID"];

        //getting restaurant details
        $query = "SELECT * FROM `Restaurant` WHERE `restaurantID`={$row["restaurantID"]}";
        $res_result = mysql_query($query);

        while ($res_row = mysql_fetch_array($res_result)){
            $deal["restName"] = $res_row["name"];
            $deal["restType"] = $res_row["type"];
            $deal["restLat"] = $res_row["lat"];          
            $deal["restLng"] = $res_row["lng"];
        } 

        // push single product into final response array
        array_push($response["deals"], $deal);
        }
        // success

        $response["success"] = 1;

        // echoing JSON response
        echo json_encode($response);
} else {
    // no products found
    $response["success"] = 0;
    $response["message"] = "No Deals found";

    // echo no users JSON
    echo json_encode($response);
}
}
else {
    // required field is missing
    $response["success"] = 0;
    $response["message"] = "Required field(s) is missing";

    // echo no users JSON
    echo json_encode($response);
   } 
?>