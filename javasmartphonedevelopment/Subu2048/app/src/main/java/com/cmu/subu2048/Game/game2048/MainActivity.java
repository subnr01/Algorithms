package com.cmu.subu2048.Game.game2048;

import com.cmu.subu2048.game2048.R;
import android.app.Activity;
import android.os.Handler;
import android.os.Message;
import android.os.Bundle;
import android.view.GestureDetector;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.widget.GridView;
import android.widget.TextView;
import android.widget.Toast;
import android.util.Log;



import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.List;
import java.util.Locale;
import java.util.Timer;
import java.util.TimerTask;


import android.hardware.Camera;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.hardware.Camera.PreviewCallback;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.preference.PreferenceManager;
import android.speech.tts.TextToSpeech;
import android.content.SharedPreferences;
import android.app.AlertDialog;
import android.content.DialogInterface;






public class MainActivity extends Activity
        implements GameStateObserver {


    private static final int UDP_SERVER_PORT = 1234;
    private static final int MAX_UDP_DATAGRAM_LEN = 1500;

    private static final String LOG_TAG = "subbu";




    Handler handler = new Handler() {

        @Override
        public void handleMessage(Message msg) {
            String message = (String) msg.obj;
            Log.v("subbu","inside handle message " +message);
            switch(message)
            {
                case "up":
                    game.slideUp();
                    break;
                case "down":
                    game.slideDown();
                    break;
                case "right":
                    game.slideRight();
                    break;
                case "left":
                    game.slideLeft();
                    break;
            }


        }
    };


    private GestureDetector gestureDetector;
    public Game game;
    private final String GAME_KEY = "Game_Parcelable";
    GameAdapter adapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        if (savedInstanceState == null) {
            game = new Game();
            game.init(this);
            initAdapter();
            initGesture();
            Log.d("subbu", "calling runGestures");
            //runGestures();
          // runUdpClient();
            runUDPThread();
            //runGabrielThread();

        }

    }




    public void runUDPThread()
    {
        Runnable r = new Runnable() {
            @Override
            public void run() {
                runUdpClient();
            }
        };
        Thread substhread = new Thread(r);
        substhread.start();
    }

    private void runUdpClient()  {
        Log.v("subbu", "running UDP client");
        String udpMsg = "hello world from UDP client " + UDP_SERVER_PORT;
        String lText;
        byte[] lMsg = new byte[MAX_UDP_DATAGRAM_LEN];
        Log.v("subbu", "running UDP client2");
        DatagramPacket dp1;
        DatagramSocket ds = null;


        Log.v("subbu", "running UDP client3");


            try {
                    ds = new DatagramSocket();
                if (ds == null)
                    Log.v("subbu","empty datagras");

                Log.v("subbu", "running UDP client4");

               // ds = new DatagramSocket();
                Log.v("subbu", "running UDP client5");

                InetAddress serverAddr = InetAddress.getByName("128.2.213.228");
                dp1 = new DatagramPacket(udpMsg.getBytes(), udpMsg.length(), serverAddr, 1234);
                Log.v("subbu", "running UDP client4");

                Log.v("subbu", "running UDP client6");
                ds.send(dp1);
                Log.v("subbu", "sending");
                DatagramPacket dp = new DatagramPacket(lMsg, lMsg.length);

                while (true) {
                    Log.v("subbu", "receiving");
                    ds.receive(dp);
                    lText = new String(lMsg, 0, dp.getLength());
                    Message msg = Message.obtain();
                    msg.obj = lText;
                    Log.i("subbu", "UDP packet received " + lText);
                    msg.setTarget(handler);
                    msg.sendToTarget();
                }
            } catch (SocketException e) {
                e.printStackTrace();
            } catch (UnknownHostException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            } catch (Exception e) {
                e.printStackTrace();
            } finally {
                    ds.close();
            }

    }


    @Override
    protected void onSaveInstanceState(Bundle outState)
    {
        super.onSaveInstanceState(outState);
        outState.putParcelable(GAME_KEY, game);
    }

    @Override
    protected void onRestoreInstanceState(Bundle inState)
    {
        game = inState.getParcelable(GAME_KEY);
        if (game == null)
            throw new UnknownError("Failed restore state");

        game.initObserver(this);
        initAdapter();
        initGesture();
        Log.d("subbu", "calling runGestures again");
        //runGestures();
        adapter.notifyDataSetChanged();
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected (MenuItem item)
    {
        if(item.getItemId() == R.id.restart)
        {
            restart();
            return true;
        }
        return false;
    }





    public void onScoresChanged(int scores)
    {
        ((TextView)findViewById(R.id.scores_value)).setText(((Integer) scores).toString());
    }
    public void onMove()
    {
        adapter.notifyDataSetChanged();
    }
    public void onStatusChanged(Status newStatus)
    {
        if(newStatus == Status.FINISHED)
        {
            Toast.makeText(this, R.string.game_over_message, Toast.LENGTH_LONG).show();
            Log.v("subbu","Exiting");
            System.exit(0);
        }

    }

    private void restart()
    {
        game.init(this);
        initAdapter();
    }

    private void initAdapter()
    {
        adapter = new GameAdapter(this, game.getField());

        GridView field = (GridView) findViewById(R.id.field);
        field.setNumColumns(game.getFieldSize());
        field.setAdapter(adapter);
    }


    private void initGesture()
    {
        gestureDetector = initGestureDetector();

        View.OnTouchListener listener = new View.OnTouchListener() {
            public boolean onTouch(View v, MotionEvent event) {
                Log.v("subbu", "initalised onTouch");
                boolean detectedUp = event.getAction() == MotionEvent.ACTION_UP;
                Log.v("subbu","event is "+detectedUp);
                boolean val = gestureDetector.onTouchEvent(event);
                Log.v("subbu", "val is "+val);
                return val;
            }
        };

        findViewById(R.id.main_screen).setOnTouchListener(listener);
        findViewById(R.id.field).setOnTouchListener(listener);
        findViewById(R.id.central_frame).setOnTouchListener(listener);
    }

    private GestureDetector initGestureDetector() {
        return new GestureDetector(this, new GestureDetector.SimpleOnGestureListener() {

            private SwipeDetector detector = new SwipeDetector();

            public boolean onDown (MotionEvent event) {
                Log.v("subbu", "onDown ");
                return true;
            }

            public boolean onSingleTapUp (MotionEvent event) {
                Log.v("subbu", "onUp ");
                return true;
            }

            public boolean onFling(MotionEvent e1, MotionEvent e2, float velocityX,
                                   float velocityY) {
                Log.d("subbu", "event detected");
                if (detector.isSwipeDown(e1, e2, velocityY)) {
                    game.slideDown();
                } else if (detector.isSwipeUp(e1, e2, velocityY)) {
                    game.slideUp();
                }else if (detector.isSwipeLeft(e1, e2, velocityX)) {
                    game.slideLeft();
                } else if (detector.isSwipeRight(e1, e2, velocityX)) {
                    game.slideRight();
                }
                return false;
            }
        });
    }

}
