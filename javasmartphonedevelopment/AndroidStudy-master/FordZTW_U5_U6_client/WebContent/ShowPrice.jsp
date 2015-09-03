<HTML>
  <HEAD>
    <TITLE>Show List</TITLE>
  </HEAD>

    <BODY>
    <%@ page import="java.util.ArrayList" %>
    <% ArrayList<String> listName = (ArrayList<String>) session.getAttribute("listName");  
       ArrayList<String> listOption = (ArrayList<String>) session.getAttribute("listOption");  
      ArrayList<String> listPrice = (ArrayList<String>) session.getAttribute("listPrice"); %>
        <H1>Here is what you selected:</H1>
        
        <table border="1">        	
        	<tr><td> <% out.print(listName.get(0)); %>
        	<td> <% out.print(listOption.get(0)); %>  
        	<td> <% out.print(listPrice.get(0)); %> 	
        	<tr><td> <% out.print(listName.get(1)); %>
        	<td> <% out.print(listOption.get(1)); %>  
        	<td> <% out.print(listPrice.get(1)); %> 
        	<tr><td> <% out.print(listName.get(2)); %>
        	<td> <% out.print(listOption.get(2)); %>  
        	<td> <% out.print(listPrice.get(2)); %> 
        	<tr><td> <% out.print(listName.get(3)); %>
        	<td> <% out.print(listOption.get(3)); %>  
        	<td> <% out.print(listPrice.get(3)); %> 
        	<tr><td> <% out.print(listName.get(4)); %>
        	<td> <% out.print(listOption.get(4)); %>  
        	<td> <% out.print(listPrice.get(4)); %> 
        	<tr><td> <% out.print(listName.get(5)); %>
        	<td> <% out.print(listOption.get(5)); %>  
        	<td> <% out.print(listPrice.get(5)); %>
        	<tr><td> <% out.print(listName.get(6)); %>
        	<td> <% out.print(listOption.get(6)); %>  
        	<td> <% out.print(listPrice.get(6)); %>
        </table>
        
   </BODY>
</HTML>