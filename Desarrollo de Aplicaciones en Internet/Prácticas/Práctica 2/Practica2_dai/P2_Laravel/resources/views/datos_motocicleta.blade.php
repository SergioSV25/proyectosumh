<!DOCTYPE html>
<html lang="eng">
<head>
	<meta charset="UTF-8">
	<title>Detalles Motocicletas Laravel</title>
</head>
<body>
	<?php
	
		foreach($datos as $dato){
			$matricula = $dato->Matricula;
			$marca = $dato->Marca;
			$modelo = $dato->Modelo;
			$anyo = $dato->Anyo;
			$color = $dato->Color;
		}
		
		echo "
		<table border=1>
		<tr><td>Matricula</td><td>Marca</td><td>Modelo</td><td>Anyo</td><td>Color</td></tr>
		
		<tr>
			<td>$matricula</td>
			<td>$marca</td>
			<td>$modelo</td>
			<td>$anyo</td>
			<td>$color</td>
		</tr>
		</table>";
		
	?>
</body>
</html>

