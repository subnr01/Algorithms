package com.cmu.subu2048.Game.game2048;

import android.content.Context;
import android.util.AttributeSet;
import android.widget.FrameLayout;
import android.util.Log;


/**
 * Square Frame layout
 */
public class SquareFrameLayout extends FrameLayout {

    public SquareFrameLayout(Context context) {
        super(context);
    }

    public SquareFrameLayout(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public SquareFrameLayout(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
    }

    @Override
    public void onMeasure(int width, int height) {
        int size = width > height ? width : height;
        super.onMeasure(size, size);
    }
}
