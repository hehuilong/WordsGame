<?php
/**
 * For getting a list of words from server
 * The words are stored and sorted by their length in the txt file dict_e
 * The file ref_dict_e stores the length line number information for quick access of a set of words whose length is limited
 * \num SerieParcourGrille
 * \brief tableau d'entiers
 */
$num = $_GET["num"];
// The max length of word
$length = $_GET["length"];
if($num<=0 || $num>15 || $length>19 || $length<3) exit("ERROR: num must be in the range of [1,15] and length must be in the range[3,19]");
// Get max line number, from the first line to this line, the words' length is less than or equal to the max length
$refLines = file("ref_dict_e");
if($refLines == FALSE) exit("ERROR: cannot load ref_dict_e file");
$line = $refLines[1+(int)$length]; // skip the first two lines cause they are the total number of lines and the max length of all the words in dict file.
$tmp = explode(" ", $line);
$maxLine = (int)$tmp[1];
// Generate randomly the line numbers in the range [1, maxLine]
$lineNumbers = Array();
while(count($lineNumbers)<$num){
	$tmp = rand(1,$maxLine);
	if(!in_array($tmp, $lineNumbers)){
		array_push($lineNumbers,$tmp);
	}
}
$words = file("dict_e");
if($words == FALSE) exit("ERROR: cannot load dict_e file");
$wordsList = rtrim($words[$lineNumbers[0]]); // rtrim - delete spaces (end of line) at the end of string
for($i=1; $i<$num; $i++){
	$ln = $lineNumbers[$i];
	$wordsList .= "#".rtrim($words[$ln]);
}
echo $wordsList;
?>