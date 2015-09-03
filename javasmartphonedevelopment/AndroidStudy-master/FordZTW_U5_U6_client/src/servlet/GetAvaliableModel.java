package servlet;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import client.Client;

/**
 * Servlet implementation class GetAvaliableModel
 */
@WebServlet("/GetAvaliableModel")
public class GetAvaliableModel extends HttpServlet {
	private static final long serialVersionUID = 1L;
    private Client client;   
    /**
     * @see HttpServlet#HttpServlet()
     */
    public GetAvaliableModel() {
        super();
        client = Client.getInstance();
		client.start();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		response.setContentType("text/html");
	    PrintWriter out = response.getWriter();
	    String title = "All available models";
	    String modelList = client.getAvaliableModel();
	    out.println(ServletUtilities.headWithTitle(title) +
                "<BODY BGCOLOR=\"#FDF5E6\">\n" +
                "<H1 ALIGN=\"CENTER\">" + title + "</H1>\n" +
                "<form action=\"ClientPage\" method=\"Get\">" );
	    out.println("<p>" + "Models:");
	    if(modelList == null) {
	    	out.println("No model available!");
	    }
	    else {
	    	String str[] = modelList.split(" ");
	    	for(int i=0; i<str.length; i++) {
	    		out.println("<input type=radio name=model value=" + str[i]+ ">" + str[i]);
	    	}
	    }
	    
	    out.println("<p>");
	    out.println("<input type=\"submit\" value=\"Done\">");
        out.println("</form ></BODY></HTML>");
	}
	
	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}
	
}
