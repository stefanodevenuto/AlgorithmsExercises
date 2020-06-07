package test;

import org.junit.*;
import static org.junit.Assert.assertEquals;
import lib.*;

public class EditDistanceTests{

  @Test
  public void editDistanceEmptyStrings(){
    assertEquals(EditDistance.editDistance("", ""), 0);
  }

  @Test
  public void editDistanceFirstStringEmpty(){
    assertEquals(EditDistance.editDistance("", "casa"), 4);
  }

  @Test
  public void editDistanceSecondStringEmpty(){
    assertEquals(EditDistance.editDistance("cassa", ""), 5);
  }

  @Test
  public void editDistanceSameStrings(){
    assertEquals(EditDistance.editDistance("pioppo", "pioppo"), 0);
  }

  @Test
  public void editDistanceRandomString(){
    assertEquals(EditDistance.editDistance("cassa", "casa"), 1);
  }

  @Test
  public void editDistanceDynEmptyStrings(){
    assertEquals(EditDistance.editDistanceDyn("", ""), 0);
  }

  @Test
  public void editDistanceDynFirstStringEmpty(){
    assertEquals(EditDistance.editDistanceDyn("", "casa"), 4);
  }

  @Test
  public void editDistanceDynSecondStringEmpty(){
    assertEquals(EditDistance.editDistanceDyn("cassa", ""), 5);
  }

  @Test
  public void editDistanceDynSameStrings(){
    assertEquals(EditDistance.editDistance("pioppo", "pioppo"), 0);
  }

  @Test
  public void editDistanceDynRandomString(){
    assertEquals(EditDistance.editDistanceDyn("cassa", "casa"), 1);
  }
  
}
