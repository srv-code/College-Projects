﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Diagnostics;

public partial class _Default : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e) {

    }

    protected void Button_Submit_Click(object sender, EventArgs e) {
        // TextBox_Data.Text = "hi";
        Debug.Print("name={0}",
            "abc");
    }
}