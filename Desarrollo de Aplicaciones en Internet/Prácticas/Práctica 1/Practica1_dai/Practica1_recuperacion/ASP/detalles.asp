<!--- #include file=conexion.asp -->
<!DOCTYPE html>
<html>
	<body>
		<%
            id_recibido = request.querystring("id")

			set consulta = conexion.Execute("select * from AVION where IDAVION=" & id_recibido)
			
			id=consulta("IDAVION")
			avion=consulta("AVION")
            plazas=consulta("N_PLAZAS")
            precio=consulta("PRECIO_BASE")
        %>

        <form action="modificar_avion.asp" method="post">
            <table>
                <tr><td>Id Avi&oacute;n:</td><td> <input type=text name=idavion readonly value="<% response.write(id) %>"></td></tr> 
                <tr><td>Avi&oacute;n:</td><td> <input type=text name=avion value="<% response.write(avion) %>"> </td></tr>     
                <tr><td>N Plazas:</td><td> <input type=text name=plazas value="<% response.write(plazas) %>"> </td></tr> 
                <tr><td>Precio Base:</td><td> <input type=text name=precio value="<% response.write(precio) %>"> </td></tr>   
			</table>
			<input type="submit" id="modificar_avion" value="Modificar avi&oacute;n"/>
        </form>
	</body>
</html>