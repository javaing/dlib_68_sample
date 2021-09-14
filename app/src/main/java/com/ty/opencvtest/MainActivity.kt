package com.ty.opencvtest

import android.app.ProgressDialog
import android.graphics.Bitmap
import android.net.Uri
import android.os.Bundle
import android.os.Environment
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_main.*
import java.io.File
import kotlin.concurrent.thread


//https://blog.csdn.net/a568478312/article/details/84790820
//用JPG無法執行，改成PNG就可以跑
//照片有兩個人頭無法辨識
//結果算準確，只是太慢

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val progress=ProgressDialog(this)
        val path = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_PICTURES).absolutePath
        //Log.e("tag", path)
        iv_origin.setImageURI(Uri.fromFile(File("$path/dlibfolder/header.png")) )
        btn_detect.setOnClickListener {
            progress.show()
            thread {
                val byte = detect()
                val b=Bitmap.createBitmap(byte, 384, 250, Bitmap.Config.ARGB_8888)
                Log.e("tag", "2: bitmap[]="+byte[0])
                runOnUiThread {
                    iv_detect.setImageBitmap(b)
                    progress.dismiss()
                }
            }
        }

    }

    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("opencv")
        }
    }

    private external fun detect():IntArray
}

