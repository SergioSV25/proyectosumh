<!DOCTYPE html>
<html lang="eng">
<head>
	<meta charset="UTF-8">
	<title>Detalles Motocicletas Laravel</title>
</head>
<body>
	<?php
		echo "
		<br>Matricula:
		<input type=text name=matricula readonly value='$dato->Matricula'>
		<br>Marca:
		<input type=text name=marca value='$dato->Marca'>
		<br>Modelo:
		<input type=text name=modelo value='$dato->Modelo'>
		<br>Anyo:
		<input type=text name=anyo value='$dato->Anyo'>
		<br>Color:
		<input type=text name=color value='$dato->Color'>";
	?>
	
</body>
</html>