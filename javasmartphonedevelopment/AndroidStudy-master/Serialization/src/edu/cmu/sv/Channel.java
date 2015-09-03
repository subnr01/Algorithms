package edu.cmu.sv;

import java.io.Serializable;
import java.util.ArrayList;

public class Channel implements Serializable {
	private static final long serialVersionUID = 1L;
	ArrayList<Video> videoClips = new ArrayList<Video>();
	public void addVideo(Video video) {
		videoClips.add(video);
	}
	public ArrayList<Video> getVideoClips() {
		return videoClips;
	}
	public void setVideoClips(ArrayList<Video> videoClips) {
		this.videoClips = videoClips;
	}
	
}
