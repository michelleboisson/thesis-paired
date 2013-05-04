package com.example.bluetoothanalog;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;

public class MyDrawingView extends View {

	public MyDrawingView(Context context) {
		super(context);
	}

	public MyDrawingView(Context context, AttributeSet attrs) {
		super(context,attrs);
	}

	public MyDrawingView(Context context, AttributeSet attrs, int defStyle) {
		super(context,attrs,defStyle);
	}
	
	
	@Override
	protected void onDraw (Canvas canvas) {
		Paint paint = new Paint();
		paint.setColor(Color.RED);
		
		canvas.drawCircle(x, y, 20, paint);		
	}

	int x = 0;
	int y = 0;
	
	public void setXandY(int xval, int yval) {
		x = xval;
		y = yval;
			
		invalidate();
	}
	
	public void setYoverTime(int yval) {
		setXandY(x+1,yval);
		if (x > this.getWidth()) {
			x = 0;
		}
	}
}
