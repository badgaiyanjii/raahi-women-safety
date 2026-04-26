package com.raahi.app

import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import android.provider.Telephony
import android.widget.Toast

class SmsReceiver : BroadcastReceiver() {
    override fun onReceive(context: Context, intent: Intent) {
        for (sms in Telephony.Sms.Intents.getMessagesFromIntent(intent)) {
            val msg = sms.messageBody
            if (msg.contains("HELP!")) {
                Toast.makeText(context, "Emergency Alert Received!", Toast.LENGTH_LONG).show()
            }
        }
    }
}
