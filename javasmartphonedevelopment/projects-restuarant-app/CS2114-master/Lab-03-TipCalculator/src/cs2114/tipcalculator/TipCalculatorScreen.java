package cs2114.tipcalculator;

import android.widget.EditText;
import android.widget.TextView;
import sofia.app.Screen;

//-------------------------------------------------------------------------
/**
 *  Write a one-sentence summary of your class here.
 *  Follow it with additional details about its purpose, what abstraction
 *  it represents, and how to use it.
 *
 *  @author  Benjamin Johnston (benjdj6)
 *  @author  Yong Kim (yak22)
 *  @version 2013.02.07
 */
public class TipCalculatorScreen extends Screen
{
	//~ Fields ................................................................
    TipCalculator calc;
    EditText amountOfBill;
    TextView tipAmount;



	//~ Public methods ........................................................

    /**
     * Initializes the TipCalculator and observer
     */
    public void intitialize()
    {
        calc = new TipCalculator();
        calc.addObserver(this);
        calc.setTipRate(0.15);
    }

    /**
     * Sets tip rate to 15% when radio button is clicked
     */
    public void tip15Clicked()
    {
        calc.setTipRate(0.15);
    }

    /**
     * Sets tip rate to 18% when radio button is clicked
     */
    public void tip18Clicked()
    {
        calc.setTipRate(0.18);
    }

    /**
     * Sets tip rate to 20% when radio button is clicked
     */
    public void tip20Clicked()
    {
        calc.setTipRate(0.20);
    }

    /**
     * Sets the amount of the bill to what is in the textfield.
     */
    public void amountOfBillEditingDone()
    {
        double amnt = Double.parseDouble(amountOfBill.getText().toString());
        calc.setAmountOfBill(amnt);
    }

    /**
     * Outputs tip amount
     */
    public void changeWasObserved(TipCalculator tc)
    {
        String.format("%.2f", calc.getTipAmount());
    }
}
