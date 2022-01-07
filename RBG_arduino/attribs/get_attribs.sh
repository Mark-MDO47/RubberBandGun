grep "<tr" D:/svnNew/SoundsSciFi/SoundsRecordedMDO/secondCut/Attributions.html | sed "s?<tr><td>?| ?" | sed "s?</td><td>? | ?g" | sed "s?</td></tr>? |?" > attribs.md
grep "<tr" D:/svnNew/SoundsSciFi/SoundsRecordedMDO/secondCut/Attributions.html | sed "s?<tr><td>?\\\\ | ?" | sed "s?</td><td>? | ?g" | sed "s?</td></tr>? |?" > attribs.txt
