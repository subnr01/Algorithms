package servlet;


import java.io.*;
import javax.servlet.*;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

import client.Client;
import customerException.OptionException;
import model.Automobile;
import model.OptionSet;

@WebServlet("/ClientPage")
public class ClientPage extends HttpServlet {
	private static final long serialVersionUID = 11;
	private String modelName;
	private Client client; 
	
	public void doGet(HttpServletRequest request,
            HttpServletResponse response) throws ServletException, IOException 
    {
		Automobile auto = null;
		response.setContentType("text/html");
		modelName = request.getParameter("model");
		client = Client.getInstance();
	    PrintWriter out = response.getWriter();
	    client.getWriter().println("c");
	    client.getWriter().println(modelName); 
	    HttpSession session = request.getSession();
	    
	    try {
	    	ObjectInputStream in = new ObjectInputStream(
					new BufferedInputStream((client.getSock()).getInputStream()));
			auto = (Automobile)in.readObject();
			
			//set session
			session.setAttribute("auto", auto);
			
			if(auto == null) {
				throw new OptionException(5); //5 stand for transmission error!
			}
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (OptionException e) {
			e.printError();
		}	    
	    
	    OptionSet color = auto.getOptionSet(0);
	    OptionSet trans = auto.getOptionSet(1);
	    OptionSet abs = auto.getOptionSet(2);
	    OptionSet airbag = auto.getOptionSet(3);
	    OptionSet moonroof = auto.getOptionSet(4);
	    String colorStr = "<select name=color>" + 
	      		"<optgroup label=\"select color\">";
	    for(int i=0; i<color.getOptionSize(); i++) {
	    	colorStr += ("<option>" + color.getOptionName(i));
	    }
	    colorStr += "</optgroup>";
	    
	    String transStr = "<select name=trans>" + 
	      		"<optgroup label=\"select transmission\">";
	    for(int i=0; i<trans.getOptionSize(); i++) {
	    	transStr += ("<option>" + trans.getOptionName(i));
	    }
	    transStr += "</optgroup>";
	    
	    String absStr = "<select name=abs>" + 
	      		"<optgroup label=\"select abs\">";
	    for(int i=0; i<abs.getOptionSize(); i++) {
	    	absStr += ("<option>" + abs.getOptionName(i));
	    }
	    absStr += "</optgroup>";
	    
	    String airbagStr = "<select name=airbag>" + 
	      		"<optgroup label=\"select airbag\">";
	    for(int i=0; i<airbag.getOptionSize(); i++) {
	    	airbagStr += ("<option>" + airbag.getOptionName(i));
	    }
	    airbagStr += "</optgroup>";
	    
	    String moonroofStr = "<select name=moonroof>" + 
	      		"<optgroup label=\"select moonroof\">";
	    for(int i=0; i<moonroof.getOptionSize(); i++) {
	    	moonroofStr += ("<option>" + moonroof.getOptionName(i));
	    }
	    moonroofStr += "</optgroup>";
	    
	    String[][] variables =
	      { { "Make/Model:",  modelName },
	        { "Color:", colorStr },
	      	{ "Transmission:", transStr },
	      	{ "ABS/Traction Control:", absStr },
	      	{ "Side Impact Air Bags:", airbagStr },
	      	{ "Power Moonroof", moonroofStr }
	      };
	    String title = "Basic Car Choice";
	    out.println(ServletUtilities.headWithTitle(title) +
	                "<BODY BGCOLOR=\"#FDF5E6\">\n" +
	                "<H1 ALIGN=\"CENTER\">" + title + "</H1>\n" +
	                "<form action=\"CalculatePrice\" method=\"Get\">" + 
	                "<TABLE BORDER=1 ALIGN=\"CENTER\">\n" +
	                "<TR BGCOLOR=\"#FFAD00\">\n" +
	                "<TH>Option<TH>Value");
	    
	    for(int i=0; i<variables.length; i++) {
	      String varName = variables[i][0];
	      String varValue = variables[i][1];
	      if (varValue == null)
	        varValue = "<I>Not specified</I>";
	      out.println("<TR><TD>" + varName + "<TD>" + varValue);
	    }
	    out.println("<TR><TD> <TD> <input type=\"submit\" value=\"Done\">");
	    out.println("</TABLE>");	   
	    out.println("</form ></BODY></HTML>");
	    
        //RequestDispatcher dispatcher = request.getRequestDispatcher(target);
        //dispatcher.forward(request, response);
	  }
	
	  /** POST and GET requests handled identically. */
	  
	  public void doPost(HttpServletRequest request,
	                     HttpServletResponse response)
	      throws ServletException, IOException 
	  {
		  doGet(request, response);
	  }
	
}