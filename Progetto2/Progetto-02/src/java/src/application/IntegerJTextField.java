package application;

import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

import javax.swing.JTextArea;

public class IntegerJTextField extends JTextArea{

	private static final long serialVersionUID = -304336001390831186L;

	public IntegerJTextField(){
        addKeyListener(new KeyAdapter() {
            public void keyTyped(KeyEvent e) {
                char ch = e.getKeyChar();

                if (!isNumber(ch) && !isValidSignal(ch) && !validatePoint(ch)  && ch != '\b') {
                    e.consume();
                }
            }
        });

    }

    private boolean isNumber(char ch){
        return ch >= '0' && ch <= '9';
    }

    private boolean isValidSignal(char ch){
        if( (getText() == null || "".equals(getText().trim()) ) && ch == '-'){
            return true;
        }

        return false;
    }

    private boolean validatePoint(char ch){
        if(ch != '.'){
            return false;
        }

        if(getText() == null || "".equals(getText().trim())){
            setText("0.");
            return false;
        }else if("-".equals(getText())){
            setText("-0.");
        }

        return true;
    }
}
