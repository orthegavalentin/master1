import java.awt.AWTException;
import java.awt.Robot;
import java.awt.Toolkit;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.StringSelection;
import java.awt.event.KeyEvent;


public class CopyPaster {


    Robot bot;

    CopyPaster()
    {
        try {
            bot = new Robot();
        } catch (AWTException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

    public void run(String cmd)
    {
        bot.keyPress(KeyEvent.VK_ALT);
        bot.keyPress(KeyEvent.VK_F2);
        bot.keyRelease(KeyEvent.VK_ALT);
        bot.keyRelease(KeyEvent.VK_F2);
        bot.delay(1000);
        StringSelection selection = new StringSelection(cmd);
        Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
        clipboard.setContents(selection, null);
        bot.delay(100);
        bot.keyPress(KeyEvent.VK_CONTROL);
        bot.keyPress(KeyEvent.VK_V);
        bot.keyRelease(KeyEvent.VK_CONTROL);
        bot.keyRelease(KeyEvent.VK_V);
        bot.delay(100);
        bot.keyPress(KeyEvent.VK_ENTER);
        bot.keyRelease(KeyEvent.VK_ENTER);
    }

    /**
     * @param args
     */
    public static void main(String[] args) {
        System.out.println(args[0]);
        CopyPaster bot = new CopyPaster();
        bot.run(args[0]);
    }

}

