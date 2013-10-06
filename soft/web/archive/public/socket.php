<?php
if(isset($_POST['coords'])) { 
    $string = "";

    $coords = $_POST['coords'];

    echo json_encode($coords);
    print_r($coords);

    foreach ($coords->points as $key => $value) {
        $string .= "(".implode(', ', array_values($value))."), ";
    }
}


// $new = $_POST['coords'];
// $boxArray = file_get_contents('ajax/box.json');
// $sentdata = json_decode($sentArray);
// $getdata = json_decode($boxArray);
// $sentdata[] = $getdata;   /* I also tried array_push($sentdata, $getdata); */
// $json = json_encode($sentdata);
// $fsize = filesize('ajax/box.json');
// if ($fsize <= 5000){
//     if (json_encode($json) != null) { /* sanity check */
//     $file = fopen('ajax/box.json' ,'w+');
//     fwrite($file, $json);
//     fclose($file);
// }else{
//     /*rest of code*/
// }


?>
<p style="font-size:20px; margin:0; padding-top:20px;">Result:</p> 
<p style="font-size:16px; margin:0; padding:0;"><?php echo $string ?></p>




