<html>
<body>

<form method=post action=eliminar_repuestos.php>
	<table border=1>
	<tr><td>Referencia</td><td>Descripcion</td><td>Importe(€)</td><td>Ganancia(%)</td><td>Borrar</td></tr>
		
<?php
include("ConexionPDO.php");
include "seguridad.php";
echo"<a href=cerrar_sesion.php>Cerrar sesion</a><br><a href=index.php>Inicio</a>";

	$sql = "SELECT * from repuestos order by Referencia";
	$consulta = $conexion->prepare($sql);
	$consulta->execute();
	$result = $consulta->fetchAll();
	

	foreach($result as $fila){
		$ref =$fila['Referencia'];
		$descrip = $fila['Descripcion'];
		$imp = $fila['Importe'];
		$ganancia = $fila['Ganancia'];

		echo "<tr>
			<td><a href=detalles_repuestos.php?referencia=$ref>$ref</b></a></td>
			<td>$descrip</td>
			<td>$imp</td>
			<td>$ganancia</td>
			<td><center><input type=checkbox name=borrar[] value=$ref</center></td></tr>";
	}
?>

</tr></table>
	<input type=submit value="Eliminar repuestos seleccionados">
	<input type=reset value="Eliminar Selecciones">
	<a href="insert_repuesto.php"><input type=button value="Añadir nuevo repuesto"></a>
</form>
</body>