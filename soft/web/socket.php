<?php
if(isset($_POST['coords'])) {
    $string = "";

    $coords = $_POST['coords'];

    foreach ($coords as $key => $value) {
        $string .= "(".implode(', ', array_values($value))."), ";
    }
}
?>
<p style="font-size:20px; margin:0; padding-top:20px;">Result:</p> 
<p style="font-size:16px; margin:0; padding:0;"><?php echo $string ?></p>




