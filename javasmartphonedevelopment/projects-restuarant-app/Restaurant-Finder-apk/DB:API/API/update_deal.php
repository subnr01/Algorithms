<?php header('Content-Type: application/json');
/*
 * Following code will list all the restaurants
 */
 
// array for JSON response
$response = array();

// include db connect class
require_once('connection.php');



// check for required fields
if (isset($_POST['restaurantID']) && isset($_POST['dealName']) && isset($_POST['price']) && isset($_POST['description'])) {
 
    $id = $_POST['id'];
    $name = $_POST['dealName'];
    $restaurantID = $_POST['restaurantID'];
    $price = $_POST['price'];
    $description = $_POST['description'];

    // mysql update row with matched pid
    $result = mysql_query("UPDATE Deals SET restaurantID = '$restaurantID', dealName = '$name', price = '$price', description = '$description' WHERE dealID = $id");
 
    // check if row inserted or not
    if ($result) {
        // successfully updated
        $response["success"] = 1;
        $response["message"] = "Restaurant successfully updated.";
 
        // echoing JSON response
        echo json_encode($response);
    } else {
 
    }
} else {
    // required field is missing
    $response["success"] = 0;
    $response["message"] = "Required field(s) is missing";
 
    // echoing JSON response
    echo json_encode($response);
}

?>