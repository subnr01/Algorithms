package edu.cmu.sv;

import java.io.Serializable;

public class Video implements Serializable {
	private static final long serialVersionUID = 1L;
	private String name;
	public Video(String name) {
		super();
		setName(name);
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	
}
