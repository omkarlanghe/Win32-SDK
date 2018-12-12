using System;
using System.Drawing;
using System.Windows.Forms;

public class CSharpWindow : Form
{
    public static void Main()
    {
        Application.Run(new CSharpWindow());
    }

    public CSharpWindow()
    {
        Icon = new Icon("myicon.ico");
        Width = 800;
        Height = 600;
        BackColor = Color.Black;
        ResizeRedraw = true;
        this.KeyDown += new KeyEventHandler(MyKeyDown);
        this.MouseDown += new MouseEventHandler(MyMouseDown);
    }
    protected override void OnPaint(PaintEventArgs pea)
    {
        Graphics grfx = pea.Graphics;
        StringFormat strfmt = new StringFormat();
        strfmt.Alignment = StringAlignment.Center;
        strfmt.LineAlignment = StringAlignment.Center;
        grfx.DrawString("HelloWorld!! My name is Omkar", Font, new SolidBrush(System.Drawing.Color.Green), ClientRectangle, strfmt);
    }
    void MyKeyDown(Object sender, KeyEventArgs e)
    {
        MessageBox.Show("Some key is Pressed..");
    }
    void MyMouseDown(Object sender, MouseEventArgs e)
    {
        MessageBox.Show("Some Mouse button is Clicked..");
    }
}


