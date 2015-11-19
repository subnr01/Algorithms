package com.cmu.subu2048.Game.game2048;

import android.content.Context;
import android.util.AttributeSet;
import android.widget.GridView;
import android.util.Log;


/**
 * Square grid view, that exactly fit into parent layout
 */
public class SquareGridView extends GridView {

    public SquareGridView(Context context) {
        super(context);
    }

    public SquareGridView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public SquareGridView(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
    }

    @Override
    public void onMeasure(int width, int height) {
        int size = width < height ? width : height;
        super.onMeasure(size, size);
    }
}