package com.example.bluetoothanalog;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.telephony.SmsMessage;
import android.util.Log;

// This will run when an SMS message comes in.
// We can see if we want to do something based upon the message
// Perhaps launch an activity
public class SMSReceive extends BroadcastReceiver 
{
	@Override
	public void onReceive(Context ctx, Intent intent) {
		Bundle bundle = intent.getExtras(); 
		Object[] pdus = (Object[]) bundle.get("pdus");
		SmsMessage[] messages = new SmsMessage[pdus.length];
		
		for (int i = 0; i < messages.length; i++){
			messages[i] = SmsMessage.createFromPdu((byte[])pdus[i]);
			Log.v("SMSFun","Body: " + messages[i].getDisplayMessageBody());
			Log.v("SMSFun","Address: " + messages[i].getDisplayOriginatingAddress());
			
			//If say we wanted to do something based on who sent it
			if (messages[i].getDisplayOriginatingAddress().contains("6463317371")){
				// we could launch an activity and pass the data
				Intent newintent = new Intent(ctx, SendBluetoothMessage.class);
				newintent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);// Pass in data
				newintent.putExtra("address", messages[i].getDisplayOriginatingAddress());
				newintent.putExtra("message", messages[i].getDisplayMessageBody());
				ctx.startActivity(newintent); 
			}
		}
	}
}