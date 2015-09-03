package servlet;
import java.io.*;
import java.util.ArrayList;

import javax.servlet.*;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;
import model.Automobile;

//ServletForwardJsp.java

@WebServlet("/CalculatePrice")
public class CalculatePrice extends HttpServlet 
{
	private static final long serialVersionUID = 2015L;
	String target = "ShowPrice.jsp";
	
	public CalculatePrice() {
		super();		
	}

    public void doGet(HttpServletRequest request, HttpServletResponse response) 
        throws ServletException, IOException 
    {
	    ArrayList<String> listName = new ArrayList<String>();
	    ArrayList<String> listPrice = new ArrayList<String>();
	    ArrayList<String> listOption = new ArrayList<String>();
	    String colorChoice = request.getParameter("color");
	    String absChoice = request.getParameter("abs");
	    String transChoice = request.getParameter("trans");
	    String airbagChoice = request.getParameter("airbag");
	    String moonroofChoice = request.getParameter("moonroof");
	    
	    HttpSession session = request.getSession();
	    Automobile auto = (Automobile) session.getAttribute("auto");
	    Float colorPrice = 0.0f;
	    System.out.println("transChoice=" + transChoice);
	    Float transPrice = auto.getOptionChoicePrice("Transmission", transChoice);
	    System.out.println("absChoice=" + absChoice);
	    Float absPrice = auto.getOptionChoicePrice("Brakes", absChoice);
	    System.out.println("airbagChoice=" + airbagChoice);
	    Float airbagPrice = auto.getOptionChoicePrice("Side Impact Air Bags", airbagChoice);
	    System.out.println("moonroofChoice=" + moonroofChoice);
	    Float moonroofPrice = auto.getOptionChoicePrice("Power Moonroof", moonroofChoice);
	    
	    Float totalPrice = auto.getBasePrice() + transPrice + absPrice + airbagPrice + moonroofPrice;
	    
	    listName.add(auto.getModel());
	    listName.add("Color"); listName.add("Transmission"); listName.add("ABS/Tranction Control");
	    listName.add("Side Impact Air Bags"); listName.add("Power Moonroof"); listName.add("Total Cost");
	    
	    listOption.add("base price");
	    listOption.add(colorChoice); listOption.add(absChoice); listOption.add(transChoice);
	    listOption.add(airbagChoice); listOption.add(moonroofChoice); listOption.add(" ");
	    
	    listPrice.add(auto.getBasePrice().toString());
	    listPrice.add(colorPrice.toString()); listPrice.add(absPrice.toString()); listPrice.add(transPrice.toString());
	    listPrice.add(airbagPrice.toString()); listPrice.add(moonroofPrice.toString()); listPrice.add(totalPrice.toString());
	    
	    session.setAttribute("listName", listName);
	    session.setAttribute("listOption", listOption);
	    session.setAttribute("listPrice", listPrice);	 
        
        RequestDispatcher dispatcher = 
            request.getRequestDispatcher(target);
        dispatcher.forward(request, response);
    } 
}
