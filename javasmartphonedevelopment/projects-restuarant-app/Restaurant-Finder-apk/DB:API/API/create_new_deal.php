 <?php
 
/*
 * Following code will create a new restaurant row
 * All restaurant details are read from HTTP Post Request
 */
 
// array for JSON response
$response1 = array();
 
//dealID`, `user_id`, `restaurantID`, `dealName`, `price`, `description`
// check for required fields
if (isset($_GET['user_id']) && isset($_GET['restaurantID']) && isset($_GET['dealName']) && isset($_GET['price']) && isset($_GET['description'])) {
 
    $name = $_GET['dealName'];
    $user_id = $_GET['user_id'];
    $restaurantID = $_GET['restaurantID'];
    $price = $_GET['price'];
    $description = $_GET['description'];
 
    // include db connect class
    require_once('connection.php');

    $result = mysql_query(	"INSERT INTO `Deals` (
`dealID` ,
`user_id` ,
`restaurantID` ,
`dealName` ,
`price` ,
`description`
) VALUES (
NULL ,  '{$user_id}',  '{$restaurantID}',  '{$name}',  '{$price}',  '{$description}'
)
") or die(mysql_error());
 
    // check if row inserted or not
    if ($result) {
        // successfully inserted into database
        $response1["success"] = 1;
        $response1["message"] = "Restaurant successfully created.";
 
        // echoing JSON response
        echo json_encode($response1);
    } else {
        // failed to insert row
        $response1["success"] = 0;
        $response1["message"] = "Oops! An error occurred.";
 
        // echoing JSON response
        echo json_encode($response1);
    }
} else {
    // required field is missing
    $response1["success"] = 0;
    $response1["message"] = "Required field(s) is missing";
 
    // echoing JSON response
    echo json_encode($response1);
}
?>